package edu.mtech.stout.core;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;


@Entity
@Table(name = "Perf_Indicator")
@NamedNativeQueries(
    {
        @NamedNativeQuery(
            name = "edu.mtech.stout.core.Performance.findAll",
            query = "SELECT * FROM Perf_Indicator",
            resultClass = Performance.class
        ),
        @NamedNativeQuery(
            name = "edu.mtech.stout.core.Performance.findByProgram",
            query = "SELECT * FROM Perf_Indicator JOIN Scale ON Perf_Indicator.scale_id = Scale.scale_id WHERE program_id = ?",
            resultClass = Performance.class
        )
    })


public class Performance  implements Serializable {
  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  @Column(name = "perf_Indicator_id")
  private long id;
  @Column(name = "scale_id")
  private long scaleId;
  @Column(name = "name")
  private String name;
  @Column(name = "desc")
  private String description;
  @Column(name = "rating")
  private int rating;

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
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

  public int getRating() {
    return rating;
  }

  public void setRating(int rating) {
    this.rating = rating;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (!(o instanceof Performance)) return false;
    Performance that = (Performance) o;
    return getId() == that.getId() &&
        scaleId == that.scaleId &&
        getRating() == that.getRating() &&
        Objects.equals(getName(), that.getName()) &&
        Objects.equals(getDescription(), that.getDescription());
  }

  @Override
  public int hashCode() {

    return Objects.hash(getId(), scaleId, getName(), getDescription(), getRating());
  }
}
