package edu.mtech.stout.db;

import edu.mtech.stout.core.User;
import org.hibernate.SessionFactory;

import java.util.List;
import java.util.Optional;

public class UserDAO extends StOutDAO<User> {

  public UserDAO(SessionFactory factory) {
    super(factory);
  }

  public Optional<User> findByUsername(String username) {
    List<User> userList = list(namedQuery("edu.mtech.stout.core.User.findByUsername")
      .setParameter(0, username));
    Optional<User> user = Optional.empty();
    if (!userList.isEmpty()) {
      user = Optional.of(userList.get(0));
    }
    return user;
  }

  public List<User> findByProgramId(Long programId) {
    return list(namedQuery("edu.mtech.stout.core.User.findByProgramId").setParameter(0, programId));
  }


  public List<User> findAll() {
    return list(namedQuery("edu.mtech.stout.core.User.findAll"));
  }

}