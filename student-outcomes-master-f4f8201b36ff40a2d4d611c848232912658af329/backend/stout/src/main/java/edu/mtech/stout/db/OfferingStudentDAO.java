package edu.mtech.stout.db;

import edu.mtech.stout.core.OfferingStudent;
import org.hibernate.SessionFactory;

import java.util.List;

public class OfferingStudentDAO extends StOutDAO<OfferingStudent>{

  public OfferingStudentDAO(SessionFactory factory) { super(factory);}

  public List<OfferingStudent> findAll() {return list(namedQuery("edu.mtech.stout.core.OfferingStudent.findAll"));}
}
