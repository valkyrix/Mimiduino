# Arduino mimikatz hash dump payload and report via email. Optimised for windows 10

**Runs mimikatz locally from a portable arduino and emails you the report.** The Budget Rubber Ducky.

mimikatz dumps the NTLM password hashes, system information and more, very useful for pentesting.

This script is optimised to run off portable arduino's such as the Arduino Pro Micro (really cheap at $3) but will also work on others. The script's size at only 6,812 bytes is perfect for small flash memory units.

#### Script run time: 5-10 seconds on an Arduino Pro Micro using the Arduino Leonardo chip

![mimikatz arduino](http://i.makeagif.com/media/11-30-2016/yz49gO.gif)

Mimicats binaries have been hardcoded but they can be changed by replacing the two url's within the powershell command.

The script has been setup to communicate with the gmail smtp server but can be used with any email provider really.

Replace `EMAIL` and `PASSWORD` placeholders with your own.
Change the SMTP server and port information if you are not using gmail as the provider.

#### Script stages

- Launch elevated command prompt and bypass UAC
- Download the correct mimikatz exe based on processor type.
- Execute mimikatz and export data.
- Email the output to selected email address as an attachment using powershell's SMTP .
- Remove all traces on the system.


