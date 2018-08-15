package edu.mtech.stout.db;

import edu.mtech.stout.core.SemesterType;
import org.hibernate.SessionFactory;
import java.util.List;

public class SemesterTypeDAO extends StOutDAO<SemesterType> {
  public SemesterTypeDAO(SessionFactory factory){
    super(factory);
  }

  public List<SemesterType> findAll(){
    return  list(namedQuery("edu.mtech.stout.core.SemesterType.findAll"));
  }
}
