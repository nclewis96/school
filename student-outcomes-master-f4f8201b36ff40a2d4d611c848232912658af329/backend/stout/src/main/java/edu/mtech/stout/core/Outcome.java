package edu.mtech.stout.core;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "Outcome")
@NamedNativeQueries(
  {
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Outcome.findAll",
      query = "SELECT * FROM Outcome",
      resultClass = Outcome.class
    ),
      @NamedNativeQuery(
          name = "edu.mtech.stout.core.Outcome.findByMetric",
          query = "SELECT * FROM Outcome WHERE metric_id = ?",
          resultClass = Outcome.class
      )

  })

public class Outcome  implements Serializable {

  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  @Column(name = "outcome_id")
  private long id;
  @Column(name = "metric_id")
  private long metricId;
  @Column(name = "name")
  private String name;
  @Column(name = "description")
  private String description;

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
  }

  public long getMetricId() {
    return metricId;
  }

  public void setMetricId(long metricId) {
    this.metricId = metricId;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public String getDescription() {
    return description;
  }

  public void setDescription(String description) {
    this.description = description;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }
    if (!(o instanceof Outcome)) {
      return false;
    }

    final Outcome that = (Outcome) o;

    return Objects.equals(this.id, that.id) &&
      Objects.equals(this.name, that.name);
  }

  @Override
  public int hashCode() {
    return Objects.hash(id, name);
  }
}
