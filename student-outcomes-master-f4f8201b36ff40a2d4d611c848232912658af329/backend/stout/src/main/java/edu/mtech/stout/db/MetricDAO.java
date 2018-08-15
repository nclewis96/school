package edu.mtech.stout.db;

import edu.mtech.stout.core.Metric;
import org.hibernate.SessionFactory;

import java.util.List;
import java.util.Optional;

public class MetricDAO extends StOutDAO<Metric> {
  public MetricDAO(SessionFactory factory) {
    super(factory);
  }


  public Optional<Metric> findByCourse(long courseId) {
    List<Metric> metricList = list(namedQuery("edu.mtech.stout.core.Metric.findByCourse")
      .setParameter(0, courseId));
    Optional<Metric> metric = Optional.empty();
    if (!metricList.isEmpty()) {
      metric = Optional.of(metricList.get(0));
    }
    return metric;
  }

  public List<Metric> findAll() {
    return list(namedQuery("edu.mtech.stout.core.Metric.findAll"));
  }

  public List<Metric> findByProgramId(long programId){
    List<Metric> metricList = list(namedQuery("edu.mtech.stout.core.Metric.findByProgramId").setParameter(0,programId));
    return metricList;
  }
}
