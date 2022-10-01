const char CONFIG_PAGE[] PROGMEM = R"=====(
<HTML>
 <HEAD>
   <TITLE>Heat Pump Controller</TITLE>
 </HEAD>
 <BODY>
  <form action="/settings" method="get">
   %s<br><br>
   <br><br>
   <input type="submit" value="Save" style='width: 150px;'>
   &nbsp;&nbsp;&nbsp;
   <a href="/reboot">
    <button type="button" style='width: 150px;'>Restart</button>
   </a>
  </form>
 </BODY>
</HTML>
)=====";

const char GET_JSON[] PROGMEM = R"=====({
 "dhw_temp":%.1f,
 "buffer_temp":%.1f,
 "inflow_temp":%.1f,
 "outflow_temp":%.1f,
 "heating":%d,
 "cooling":%d,
 "dhw_heating":%d,
 "dhw_direct_heating": %d,
 "rssi":%d,
})=====";