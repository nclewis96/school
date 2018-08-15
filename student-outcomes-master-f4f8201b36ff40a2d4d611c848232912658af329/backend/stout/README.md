# StOut

How to start the StOut application
---

1. Run `mvn clean install` to build your application in backend/stout
1. Use winscp to move the stout-0.1jar to csdept29.mtech.edu
1. Start application with `java -jar target/stout-0.1.jar server config.yml`
1. Deploy front end.
1. To check that your application is running enter url `http://localhost:8080`

Health Check
---

To see your applications health enter url `http://localhost:8081/healthcheck`
