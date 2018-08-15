package edu.mtech.stout.auth;

import edu.mtech.stout.core.Role;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.RoleDAO;
import io.dropwizard.auth.Authorizer;
import io.dropwizard.hibernate.UnitOfWork;

import java.util.HashSet;
import java.util.List;

public class StOutAuthorizer implements Authorizer<User> {

  RoleDAO roleDao;

  public StOutAuthorizer(RoleDAO roleDao) {
    this.roleDao = roleDao;
  }

  @Override
  @UnitOfWork
  public boolean authorize(User user, String role) {
    List<Role> userRoles = roleDao.getByUserId(user.getId());
    HashSet<String> stringRoles = new HashSet<>();
    for (Role userRole : userRoles) {
      stringRoles.add(userRole.getName());
    }
    return stringRoles.contains(role);
  }
}
