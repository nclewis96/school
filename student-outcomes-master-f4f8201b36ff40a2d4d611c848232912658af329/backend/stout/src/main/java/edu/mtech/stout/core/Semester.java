package edu.mtech.stout.core;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "Semester")
@NamedNativeQueries(
  {
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Semester.findAll",
      query = "SELECT * FROM Semester",
      resultClass = Semester.class
    )
  })
public class Semester  implements Serializable {
  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  @Column(name = "semester_id")
  private long id;
  @Column(name = "semester_type_id")
  private long typeId;
  @Column(name = "year")
  private int year;

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
  }

  public long getTypeId() {
    return typeId;
  }

  public void setTypeId(long typeId) {
    this.typeId = typeId;
  }

  public int getYear() {
    return year;
  }

  public void setYear(int year) {
    this.year = year;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }
    if (!(o instanceof Semester)) {
      return false;
    }

    final Semester that = (Semester) o;

    return Objects.equals(this.id, that.id) &&
      Objects.equals(this.year, that.year);
  }

  @Override
  public int hashCode() {
    return Objects.hash(id, year, typeId);
  }
}
