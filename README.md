# lightMobileMints

## Cronjob 
```
@reboot cd /home/teamlary/gitHubRepos/fleetSensing/firmware/xu4_mqtt && ./runAll.sh
*/1 * * * * rsync -avzrtu -e "ssh -p 2222" /home/teamlary/mintsData/raw/ mints@mintsdata.utdallas.edu:raw/
*/5 * * * * cd /home/teamlary/gitHubRepos/fleetSensing/firmware/xu4_mqtt && python3 deleter.py
```
