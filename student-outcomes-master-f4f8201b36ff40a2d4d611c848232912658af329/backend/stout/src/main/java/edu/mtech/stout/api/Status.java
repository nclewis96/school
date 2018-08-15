package edu.mtech.stout.api;

import com.fasterxml.jackson.annotation.JsonProperty;

public class Status {
  @JsonProperty
  String message;
  @JsonProperty
  String resource;
  @JsonProperty
  String action;
  @JsonProperty
  long id;

  public int getStatus() {
    return status;
  }

  public void setStatus(int status) {
    this.status = status;
  }

  @JsonProperty
  int status;

  public String getMessage() {
    return message;
  }

  public void setMessage(String message) {
    this.message = message;
  }

  public String getResource() {
    return resource;
  }

  public void setResource(String resource) {
    this.resource = resource;
  }

  public String getAction() {
    return action;
  }

  public void setAction(String action) {
    this.action = action;
  }

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
  }
}
