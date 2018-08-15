package edu.mtech.stout.db;

import edu.mtech.stout.core.Scale;
import org.hibernate.SessionFactory;

import java.util.List;

public class ScaleDAO extends StOutDAO<Scale> {
  public ScaleDAO(SessionFactory factory) {
    super(factory);
  }

  public List<Scale> findAll() {
    return list(namedQuery("edu.mtech.stout.core.Scale.findAll"));
  }

  public List<Scale> findByProgram(Long programId){
    return list(namedQuery("edu.mtech.stout.core.Scale.findByProgram").setParameter(0,programId));
  }
}
