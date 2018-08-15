package edu.mtech.stout.db;

import edu.mtech.stout.core.Semester;
import org.hibernate.SessionFactory;

import java.util.List;


public class SemesterDAO extends StOutDAO<Semester> {
  public SemesterDAO(SessionFactory factory) {
    super(factory);
  }

  public List<Semester> findAll() {
    return list(namedQuery("edu.mtech.stout.core.Semester.findAll"));
  }

}
