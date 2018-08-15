package edu.mtech.stout.auth;

import edu.mtech.stout.api.AuthenticationObject;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.UserDAO;
import io.dropwizard.auth.AuthenticationException;
import io.dropwizard.auth.Authenticator;
import io.dropwizard.hibernate.UnitOfWork;

import java.util.Optional;


public class StOutAuthenticator implements Authenticator<AuthenticationObject, User> {

  private UserDAO userDao;

  public StOutAuthenticator(UserDAO userDao) {
    super();
    this.userDao = userDao;
  }

  @Override
  @UnitOfWork
  public Optional<User> authenticate(AuthenticationObject authObj) {
    String username = authObj.retrieveUsername();
    if (username != null) {
      return userDao.findByUsername(username);
    }
    return Optional.empty();
  }

}
