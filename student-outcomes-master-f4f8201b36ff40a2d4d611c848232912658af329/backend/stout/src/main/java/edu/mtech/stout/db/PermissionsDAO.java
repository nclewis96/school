package edu.mtech.stout.db;

import edu.mtech.stout.core.Permissions;
import org.hibernate.SessionFactory;

import java.util.List;

public class PermissionsDAO extends StOutDAO<Permissions> {
  public PermissionsDAO(SessionFactory factory) {super(factory);}

  public List<Permissions> findByUserId(long userId){
    return list(namedQuery("edu.mtech.stout.core.Permissions.findByUserId").setParameter(0,userId));
  }
  public List<Permissions> findAll(){return list(namedQuery("edu.mtech.stout.core.Permissions.findAll"));}
}
