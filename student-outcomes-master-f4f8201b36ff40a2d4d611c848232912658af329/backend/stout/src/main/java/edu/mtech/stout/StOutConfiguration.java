package edu.mtech.stout;

import com.fasterxml.jackson.annotation.JsonProperty;
import io.dropwizard.Configuration;
import io.dropwizard.client.JerseyClientConfiguration;
import io.dropwizard.db.DataSourceFactory;
import org.hibernate.validator.constraints.NotEmpty;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;

public class StOutConfiguration extends Configuration {
  /********************************************************************
   * CLIENT
   ********************************************************************/
  @Valid
  @NotNull
  private JerseyClientConfiguration jerseyClient = new JerseyClientConfiguration();

  @JsonProperty("jerseyClient")
  public JerseyClientConfiguration getJerseyClientConfiguration() {
    return jerseyClient;
  }

  @JsonProperty("jerseyClient")
  public void setJerseyClientConfiguration(JerseyClientConfiguration jerseyClient) {
    this.jerseyClient = jerseyClient;
  }

  /********************************************************************
   * DATABASE
   ********************************************************************/
  @Valid
  @NotNull
  private DataSourceFactory database = new DataSourceFactory();

  @JsonProperty("database")
  public void setDataSourceFactory(DataSourceFactory factory) {
    this.database = factory;
  }

  @JsonProperty("database")
  public DataSourceFactory getDataSourceFactory() {
    return database;
  }

  /*******************************************************************
   * CAS Auth and Service Config
   ********************************************************************/
  // TODO: implement service configuration
  @NotEmpty
  private String service;

  @NotEmpty
  private String casURL;

  @NotEmpty
  private String jwtSecret;

  @JsonProperty
  public String getService() {
    return service;
  }

  @JsonProperty
  public void setService(String service) {
    this.service = service;
  }

  @JsonProperty
  public String getCasURL() {
    return casURL;
  }

  @JsonProperty
  public void setCasURL(String casURL) {
    this.casURL = casURL;
  }

  @JsonProperty
  public String getJwtSecret() {
    return jwtSecret;
  }

  @JsonProperty
  public void setJwtSecret(String jwtSecret) {
    this.jwtSecret = jwtSecret;
  }
}
