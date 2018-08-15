package edu.mtech.stout.core;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "Offering_Student")
@NamedNativeQueries(
    {
        @NamedNativeQuery(
            name = "edu.mtech.stout.core.OfferingStudent.findAll",
            query = "SELECT * FROM Offering_Student",
            resultClass =  OfferingStudent.class
        )
    })

public class OfferingStudent  implements Serializable {
  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  @Column(name = "student_id")
  private long id;
  @Column(name = "offering_id")
  private long offeringId;
  @Column(name = "student_name")
  private String name;

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
  }

  public long getOfferingId() {
    return offeringId;
  }

  public void setOfferingId(long offeringId) {
    this.offeringId = offeringId;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (!(o instanceof OfferingStudent)) return false;
    OfferingStudent that = (OfferingStudent) o;
    return getId() == that.getId() &&
        getOfferingId() == that.getOfferingId() &&
        Objects.equals(getName(), that.getName());
  }

  @Override
  public int hashCode() {

    return Objects.hash(getId(), getOfferingId(), getName());
  }
}
