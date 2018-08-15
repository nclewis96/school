package edu.mtech.stout.core;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Date;
import java.util.Objects;

@Entity
@Table(name = "Program_Permissions")
@NamedNativeQueries(
    {
        @NamedNativeQuery(
            name = "edu.mtech.stout.core.Permissions.findAll",
            query = "SELECT * FROM Program_Permissions",
            resultClass = Permissions.class
        ),
        @NamedNativeQuery(
            name = "edu.mtech.stout.core.Permissions.findByUserId",
            query = "SELECT * FROM Program_Permissions JOIN Users ON Users.user_id = Program_Permissions.user_id WHERE Users.user_id = ?",
            resultClass = Permissions.class
        )
    })
public class Permissions  implements Serializable {
  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  @Column(name = "program_permission_id")
  private long id;
  @Column(name = "permission_id")
  private long permissionId;
  @Column(name = "user_id")
  private long userId;
  @Column(name = "program_id")
  private long programId;

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
  }

  public long getPermissionId() {
    return permissionId;
  }

  public void setPermissionId(long permissionId) {
    this.permissionId = permissionId;
  }

  public long getUserId() {
    return userId;
  }

  public void setUserId(long userId) {
    this.userId = userId;
  }

  public long getProgramId() {
    return programId;
  }

  public void setProgramId(long programId) {
    this.programId = programId;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (!(o instanceof Permissions)) return false;
    Permissions that = (Permissions) o;
    return getId() == that.getId() &&
        getPermissionId() == that.getPermissionId() &&
        getUserId() == that.getUserId() &&
        getProgramId() == that.getProgramId();
  }

  @Override
  public int hashCode() {

    return Objects.hash(getId(), getPermissionId(), getUserId(), getProgramId());
  }
}
