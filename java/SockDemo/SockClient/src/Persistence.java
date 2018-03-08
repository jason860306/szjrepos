import java.io.*;

class Person implements Serializable {
	private static final long serialVersionUID = 4513221427669572239L;
	private String name;
	private String sex;
	private String birthday;
	private String addr;
	private String street;
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getSex() {
		return sex;
	}
	public void setSex(String sex) {
		this.sex = sex;
	}
	public String getBirthday() {
		return birthday;
	}
	public void setBirthday(String birthday) {
		this.birthday = birthday;
	}
	public String getAddr() {
		return addr;
	}
	public void setAddr(String addr) {
		this.addr = addr;
	}
	public String getStreet() {
		return street;
	}
	public void setStreet(String street) {
		this.street = street;
	}
}

public class Persistence implements Serializable {

	private Person person;
	
	public Persistence() {
		person = new Person();
		person.setName("Jack");
		person.setSex("M");
		person.setBirthday("2013");
		person.setStreet("shangdi");
		person.setAddr("beijing");
	}
	
	public byte[] toBytes() {
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		try {
			ObjectOutputStream obout = new ObjectOutputStream(out);
			obout.writeObject(person);
		} catch (IOException e) {
			e.printStackTrace();
		}
		return out.toByteArray();
	}
	
	public Person readBytes(byte[] bs) {
		Person person = null;
		try {
			ByteArrayInputStream byteIn = new ByteArrayInputStream(bs);
			ObjectInputStream in = new ObjectInputStream(byteIn);
			person = (Person)in.readObject();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return person ;
	}

	public Person getPeron() {
		return person;
	}

	public void setPeron(Person person) {
		this.person = person;
	}

}
