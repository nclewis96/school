package edu.mtech.stout.db;

import edu.mtech.stout.core.Offering;
import org.hibernate.SessionFactory;

import java.util.List;
import java.util.Optional;

public class OfferingDAO extends StOutDAO<Offering> {
  public OfferingDAO(SessionFactory factory) {
    super(factory);
  }

  public List<Offering> findByProgramId(long programId){
    List<Offering> offeringList = list(namedQuery("edu.mtech.stout.core.Offering.findByProgramId").setParameter(0,programId));
    return offeringList;
  }
  public Optional<Offering> findByCourse(long courseId) {
    List<Offering> offeringList = list(namedQuery("edu.mtech.stout.core.Offering.findByCourse")
      .setParameter(0, courseId));
    Optional<Offering> user = Optional.empty();
    if (!offeringList.isEmpty()) {
      user = Optional.of(offeringList.get(0));
    }
    return user;
  }

  public List<Offering> findByUser(long userId){
    return list(namedQuery("edu.mtech.stout.core.Offering.findByUser").setParameter(0,userId));
  }

  public List<Offering> findAll() {
    return list(namedQuery("edu.mtech.stout.core.Offering.findAll"));
  }
}
