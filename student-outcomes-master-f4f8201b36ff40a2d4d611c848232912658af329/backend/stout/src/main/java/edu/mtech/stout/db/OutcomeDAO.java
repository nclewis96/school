package edu.mtech.stout.db;

import edu.mtech.stout.core.Outcome;
import org.hibernate.SessionFactory;

import java.util.List;
import java.util.Optional;

public class OutcomeDAO extends StOutDAO<Outcome> {
  public OutcomeDAO(SessionFactory factory) {
    super(factory);
  }


  public Optional<Outcome> findByName(String name) {
    List<Outcome> outcomeList = list(namedQuery("edu.mtech.stout.core.Outcome.findByName")
      .setParameter(0, name));
    Optional<Outcome> outcome = Optional.empty();
    if (!outcomeList.isEmpty()) {
      outcome = Optional.of(outcomeList.get(0));
    }
    return outcome;
  }

  public List<Outcome> findAll() {
    return list(namedQuery("edu.mtech.stout.core.Outcome.findAll"));
  }

  public List<Outcome> findByMetric(long metricId){
    List<Outcome>  outcomeList = list(namedQuery("edu.mtech.stout.core.Outcome.findByMetric").setParameter(0,metricId));
    return outcomeList;
  }

}
