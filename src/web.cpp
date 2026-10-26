#include "web.h"
#include "pid.h"
#include <Preferences.h>
#include <WebServer.h>
#include <WiFi.h>

static WebServer server(80);
static Preferences prefs;

static const char PAGE[] PROGMEM = R"HTML(<!doctype html>
<html><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>Pata Negra</title>
<style>
body{font-family:system-ui;background:#111;color:#eee;max-width:420px;margin:0 auto;padding:16px}
label{display:block;margin-top:14px;font-size:14px;color:#aaa}
input{width:100%;box-sizing:border-box;font-size:20px;padding:10px;background:#222;color:#fff;border:1px solid #444;border-radius:8px}
button{margin-top:20px;width:100%;font-size:20px;padding:14px;border:0;border-radius:8px;background:#2e7d32;color:#fff}
#s{margin-top:10px;color:#8bc34a;min-height:20px}
</style></head><body>
<h2>Pata Negra - PID</h2>
<label>Kp</label><input id="kp" type="number" step="0.005">
<label>Kd</label><input id="kd" type="number" step="0.05">
<label>kFreno</label><input id="kf" type="number" step="0.005">
<label>PWM base (0-255)</label><input id="pwm" type="number" step="5">
<button onclick="aplicar()">Aplicar</button>
<div id="s"></div>
<script>
const ids=['kp','kd','kf','pwm'];
fetch('/get').then(r=>r.json()).then(d=>ids.forEach(i=>document.getElementById(i).value=d[i]));
function aplicar(){
  const q=ids.map(i=>i+'='+document.getElementById(i).value).join('&');
  fetch('/set?'+q).then(r=>r.text()).then(t=>{document.getElementById('s').textContent=t;});
}
</script></body></html>)HTML";

static void handleRoot() { server.send_P(200, "text/html", PAGE); }

static void handleGet() {
  String j = "{\"kp\":" + String(pid.getKp(), 4) + ",\"kd\":" + String(pid.getKd(), 4) +
             ",\"kf\":" + String(pid.getKFreno(), 4) + ",\"pwm\":" + String(pid.getPwmBase()) + "}";
  server.send(200, "application/json", j);
}

static void handleSet() {
  float kp = server.hasArg("kp") ? server.arg("kp").toFloat() : pid.getKp();
  float kd = server.hasArg("kd") ? server.arg("kd").toFloat() : pid.getKd();
  float kf = server.hasArg("kf") ? server.arg("kf").toFloat() : pid.getKFreno();
  int pwm = server.hasArg("pwm") ? server.arg("pwm").toInt() : pid.getPwmBase();

  pid.setParams(kp, kd, kf, pwm);

  prefs.putFloat("kp", pid.getKp());
  prefs.putFloat("kd", pid.getKd());
  prefs.putFloat("kf", pid.getKFreno());
  prefs.putInt("pwm", pid.getPwmBase());

  server.send(200, "text/plain", "Aplicado y guardado");
}

static void webTask(void *) {
  for (;;) {
    server.handleClient();
    vTaskDelay(pdMS_TO_TICKS(2));
  }
}

void webBegin() {
  prefs.begin("pid", false);
  pid.setParams(prefs.getFloat("kp", pid.getKp()), prefs.getFloat("kd", pid.getKd()),
                prefs.getFloat("kf", pid.getKFreno()), prefs.getInt("pwm", pid.getPwmBase()));

  WiFi.mode(WIFI_AP);
  WiFi.softAP("PataNegra", "12345678");

  server.on("/", handleRoot);
  server.on("/get", handleGet);
  server.on("/set", handleSet);
  server.begin();

  xTaskCreatePinnedToCore(webTask, "web", 6144, nullptr, 1, nullptr, 0);
}
