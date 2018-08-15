package edu.mtech.stout.core;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "Scale")
@NamedNativeQueries(
  {
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Scale.findAll",
      query = "SELECT * FROM Scale",
      resultClass = Scale.class
    ),
      @NamedNativeQuery(
          name = "edu.mtech.stout.core.Scale.findByProgram",
          query = "SELECT * FROM Scale WHERE program_id = ?",
          resultClass = Scale.class
      )
  })
public class Scale  implements Serializable {
  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  @Column(name = "scale_id")
  private long id;
  @Column(name = "name")
  private String name;
  @Column(name = "desc")
  private String desc;
  @Column(name = "program_id")
  private long progId;

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

  public String getDesc() {
    return desc;
  }

  public void setDesc(String desc) {
    this.desc = desc;
  }

  public long getProgId() {
    return progId;
  }

  public void setProgId(long progId) {
    this.progId = progId;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }
    if (!(o instanceof Scale)) {
      return false;
    }

    final Scale that = (Scale) o;

    return Objects.equals(this.id, that.id) &&
      Objects.equals(this.progId, that.progId);
  }

  @Override
  public int hashCode() {
    return Objects.hash(id, progId, name);
  }
}
