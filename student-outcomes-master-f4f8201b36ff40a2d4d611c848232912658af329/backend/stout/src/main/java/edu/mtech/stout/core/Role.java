package edu.mtech.stout.core;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;


@Entity
@Table(name = "Roles")
@NamedNativeQueries(
  {
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Role.findAll",
      query = "SELECT * FROM Roles",
      resultClass = Role.class
    ),
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Role.getByUserId",
      query = "SELECT * FROM Roles WHERE permission_id in (SELECT Roles.permission_id" +
        " FROM Roles JOIN Program_Permissions ON Roles.permission_id = Program_Permissions.permission_id " +
        "JOIN Users ON Users.user_id = Program_Permissions.user_id WHERE Users.user_id = ?)",
      resultClass = Role.class
    )
  })
public class Role  implements Serializable {
  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  @Column(name = "permission_id")
  private long id;
  @Column(name = "name")
  private String name;

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

  @Override
  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }
    if (!(o instanceof Role)) {
      return false;
    }

    final Role that = (Role) o;

    return Objects.equals(this.id, that.id) &&
      Objects.equals(this.name, that.name);
  }

  @Override
  public int hashCode() {
    return Objects.hash(id, name);
  }
}
