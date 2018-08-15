package edu.mtech.stout.client;

import edu.mtech.stout.StOutConfiguration;

import javax.ws.rs.client.Client;
import javax.ws.rs.client.Invocation;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

public class CASValidator {
  private StOutConfiguration config;
  private Client client;

  public CASValidator(StOutConfiguration config, Client client) {
    this.config = config;
    this.client = client;
  }

  public String validateTicket(String ticket, String service) {
    WebTarget webResource = client.target(config.getCasURL()).path("");
    webResource = webResource.queryParam("ticket", ticket);
    webResource = webResource.queryParam("service", service);
    webResource = webResource.queryParam("format", "JSON");
    Invocation.Builder invocationBuilder = webResource.request(MediaType.APPLICATION_JSON);
    Response response = invocationBuilder.get();
    String casResponse = response.readEntity(String.class);
    if (!casResponse.contains("<cas:user>")) {
      return null;
    }
    casResponse = casResponse.substring(casResponse.indexOf("<cas:user>") + 10, casResponse.indexOf("</cas:user>"));
    return casResponse.trim();
  }
}
