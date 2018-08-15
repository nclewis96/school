package edu.mtech.stout.db;

import edu.mtech.stout.core.Performance;
import org.hibernate.SessionFactory;

import java.util.List;

public class PerformanceDAO extends  StOutDAO<Performance>{
  public PerformanceDAO(SessionFactory factory) {super(factory);}

  public List<Performance> findAll() {
    return  list(namedQuery("edu.mtech.stout.core.Performance.findAll"));
  }

  public List<Performance> findByProgram(Long programId){
    return list(namedQuery("edu.mtech.stout.core.Performance.findByProgram").setParameter(0, programId));
  }
}

