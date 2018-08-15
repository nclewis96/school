package edu.mtech.stout.db;

import edu.mtech.stout.core.Offering;
import edu.mtech.stout.core.OfferingOutcome;
import org.hibernate.SessionFactory;
import java.util.List;

public class OfferingOutcomeDAO extends StOutDAO<OfferingOutcome>{
  public OfferingOutcomeDAO(SessionFactory factory) { super(factory);}

  public List<OfferingOutcome> findProgramId(long programId){
    return list(namedQuery("edu.mtech.stout.core.OfferingOutcome.findProgramId").setParameter(0,programId));
  }
  public List<OfferingOutcome> findAll(){
    return list(namedQuery("edu.mtech.stout.core.OfferingOutcome.findAll"));
  }
}
