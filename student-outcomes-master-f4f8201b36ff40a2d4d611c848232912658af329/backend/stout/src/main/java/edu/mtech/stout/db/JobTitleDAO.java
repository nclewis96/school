package edu.mtech.stout.db;

import edu.mtech.stout.core.JobTitle;
import org.hibernate.SessionFactory;

import java.util.List;

public class JobTitleDAO extends StOutDAO<JobTitle> {
  public JobTitleDAO(SessionFactory factory) {
    super(factory);
  }

  public List<JobTitle> findAll() {
    return list(namedQuery("edu.mtech.stout.core.JobTitle.findAll"));
  }

  public List<JobTitle> getByUserId(long id) {
    return list(namedQuery("edu.mtech.stout.core.JobTitle.getByUserId").setParameter(0, id));
  }

}
