package edu.mtech.stout.db;

import edu.mtech.stout.core.Role;
import org.hibernate.SessionFactory;

import java.util.List;

public class RoleDAO extends StOutDAO<Role> {
  public RoleDAO(SessionFactory factory) {
    super(factory);
  }


//  public Optional<Role> findByCourse(long courseId) {
//    List<Role> rolesList = list(namedQuery("edu.mtech.stout.core.Role.findByCourse")
//      .setParameter(0, courseId));
//    Optional<Role> role = Optional.empty();
//    if(!rolesList.isEmpty()){
//      role = Optional.of(rolesList.get(0));
//    }
//    return role;
//  }

  public List<Role> findAll() {
    return list(namedQuery("edu.mtech.stout.core.Role.findAll"));
  }

  public List<Role> getByUserId(long id) {
    return list(namedQuery("edu.mtech.stout.core.Role.getByUserId").setParameter(0, id));
  }

}
