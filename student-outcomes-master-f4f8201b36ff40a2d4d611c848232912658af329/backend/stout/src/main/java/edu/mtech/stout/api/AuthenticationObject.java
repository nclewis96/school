package edu.mtech.stout.api;

import com.auth0.jwt.JWT;
import com.auth0.jwt.JWTVerifier;
import com.auth0.jwt.algorithms.Algorithm;
import com.auth0.jwt.exceptions.JWTCreationException;
import com.auth0.jwt.exceptions.JWTDecodeException;
import com.auth0.jwt.exceptions.JWTVerificationException;
import com.auth0.jwt.interfaces.DecodedJWT;
import com.fasterxml.jackson.annotation.JsonProperty;

import java.io.UnsupportedEncodingException;
import java.util.Calendar;
import java.util.Date;

public class AuthenticationObject {

  @JsonProperty
  private String jwt;

  @JsonProperty
  private String username;

  @JsonProperty
  private UserApi user;

  private DecodedJWT decodedJWT = null;

  private static String service = "";
  private static String secret = "";

  @JsonProperty
  public String getJwt() {
    return jwt;
  }

  @JsonProperty
  public void setJwt(String jwt) {
    this.jwt = jwt;
  }

  public void createJwt() {
    try {
      Algorithm algorithm = Algorithm.HMAC512(secret);
      Calendar expireCal = Calendar.getInstance();
      expireCal.add(Calendar.HOUR, 2);
      Date expiry = expireCal.getTime();
      this.jwt = JWT.create()
        .withIssuer(service)
        .withClaim("username", username)
        .withExpiresAt(expiry)
        .sign(algorithm);
    } catch (UnsupportedEncodingException exception) {
      //UTF-8 encoding not supported
    } catch (JWTCreationException exception) {
      //Invalid Signing configuration / Couldn't convert Claims.
    }
  }

  private boolean verifyJwt() {
    try {
      Algorithm algorithm = Algorithm.HMAC512(secret);
      JWTVerifier verifier = JWT.require(algorithm)
        .withIssuer(service)
        .build(); //Reusable verifier instance
      decodedJWT = verifier.verify(this.jwt);
    } catch (UnsupportedEncodingException exception) {
      //UTF-8 encoding not supported
      return false;
    } catch (JWTVerificationException exception) {
      //Invalid signature/claims
      return false;
    }
    return true;
  }

  private boolean decodeJwt() {
    if (verifyJwt()) {
      try {
        this.decodedJWT = JWT.decode(jwt);
      } catch (JWTDecodeException exception) {
        return false;
      }
      return true;
    }
    return false;
  }

  public String retrieveUsername() {
    username = null;
    if (decodeJwt()) {
      username = decodedJWT.getClaims().get("username").asString();
    }
    return username;
  }

  public String getUsername() {
    return username;
  }

  @JsonProperty
  public void setUsername(String username) {
    this.username = username;
  }

  public static void setService(String newService) {
    service = newService;
  }

  public static void setSecret(String newSecret) {
    secret = newSecret;
  }

  @JsonProperty
  public UserApi getUser() {
    return user;
  }

  public void setUser(UserApi user) {
    this.user = user;
  }

}

