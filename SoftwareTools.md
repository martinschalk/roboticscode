# Tortoise SVN #

http://tortoisesvn.net/downloads.html

# PSoC Creator #

## 01.08.2014 - controller not in device list ##
- Problem: PsoC Creator 3.0 will not compile device CY8C55\*AXI-060 <br>
- Reason: Device no longer supported. (does not appear in device list) <br>
- Solution: Using PsoC Creator 2.2 <br>

<h2>20.10.2014 - linker problem</h2>
- Problem: linker or compiler does not distinguish between "BAL_SendMsg" and 2BAL_SendServoMsg", calling BAL_SendServoMsg resulted in executing "BAL_SendMsg" <br>
- Reason: Unknown, probably function name too long <br>
- Solution: Renaming functions <br>

<h1>USB to UART Bridge</h1>

- Driver: <a href='http://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx'>http://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx</a>
- Manual: <a href='http://www.silabs.com/Support%20Documents/TechnicalDocs/an197.pdf'>http://www.silabs.com/Support%20Documents/TechnicalDocs/an197.pdf</a>

- Terminal-Tool: RealTerm