package edu.mtech.stout.core;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "Metric")
@NamedNativeQueries(
  {
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Metric.findAll",
      query = "SELECT * FROM Metric",
      resultClass = Metric.class
    ),
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Metric.findByProgramId",
      query = "SELECT * FROM Metric WHERE program_id = ?",
      resultClass = Metric.class
    )
  })
public class Metric  implements Serializable {
  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  @Column(name = "metric_id")
  private long id;
  @Column(name = "program_id")
  private long programId;
  @Column(name = "name")
  private String name;

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
  }

  public long getProgramId() {
    return programId;
  }

  public void setProgramId(long programId) {
    this.programId = programId;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }
    if (!(o instanceof Metric)) {
      return false;
    }

    final Metric that = (Metric) o;

    return Objects.equals(this.id, that.id) &&
      Objects.equals(this.name, that.name);
  }

  @Override
  public int hashCode() {
    return Objects.hash(id, name, programId);
  }
}
