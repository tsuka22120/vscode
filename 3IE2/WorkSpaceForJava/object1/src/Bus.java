public class Bus extends Car {
  int passenger;
  public Bus() {
    System.out.println("バス製造");
  }

  //乗客の設定を行う
  public void setPassenger() {
    this.passenger = 0;
    System.out.println("搭乗人数: " + passenger);
  }
  //燃料の設定を行う
  public void setGas() {
    this.gas = 20;
    System.out.println("搭載燃料：" + getGas());
  }
  //燃費の設定を行う。
  public void setNenpi() {
    this.nenpi = 10;
    System.out.println("燃費：" + getNenpi());
  }
  
}
