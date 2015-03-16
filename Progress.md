## 27.07.2014 ##
- Project started <br>
- SVN server and wiki page prepared <br>
- prototype of bus created <br>

<h2>15.08.2014</h2>
- Problem with new PSoC Creator 3.0 solved (see <a href='https://code.google.com/p/roboticscode/wiki/SoftwareTools'>https://code.google.com/p/roboticscode/wiki/SoftwareTools</a>) <br>
- Software timer module created and tested <br>
- Bus implemented (hal, bpl, bal) <br>
- Bus tests with second uart <br>

<h2>11.10.2014</h2>
- Servo messages !Ping() and CheckResponse() prepared <br>
- Error codes of Response Packet implemented<br>
<br>
<h2>20.10.2014</h2>
- Transmit chain tested and revised<br>
- fixed linker problem (!BAL_SendMsg = !BAL_SendServoMsg)<br>
<br>
<h2>13.01.2015</h2>
- structure of motor message revised and adjusted in bal and bpl module (not yet tested)<br>
<br>
<h2>20.01.2015</h2>
- USB to UART Bridge driver installed <br>
- RealTerm installed and tested <br>
- Psoc Design adjusted (Test Uart deactivated, rx-pin configured as input) <br>
- function !HAL_GetByte tested by sending messages with RealTerm --> receiving something different, bit oder inverted? <br>

<h2>12.02.2015</h2>
- task scheduler implemented <br>
- bal test added (ping) <br>
- error expected in TMR module, probably exceeding number of timers, seems to be a pointer problem <br>

<h2>21.02.2015</h2>
- error module created and RxCount, TxCount registered to be observed by error handler <br>
- compiler warning eliminated (cast) <br>
- ticket for cm3 reset problem opened at cypress forum: <a href='http://www.cypress.com/?app=forum&id=2233&rID=108020'>http://www.cypress.com/?app=forum&amp;id=2233&amp;rID=108020</a> <br>

<h2>23.02.2015</h2>
- error found! ring buffer overrunning in function BPL_TransmitMessage() <br>