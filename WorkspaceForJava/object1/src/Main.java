public class Main {
    public static void main(String args[]) {
        System.out.println("===バス===");
        Bus bus = new Bus();
        bus.setGas();
        bus.setTire(6);
        bus.setNenpi();
        bus.drive();
        bus.drive();
        bus.drive();
        bus.drive();
        System.out.println("===救急車===");
        Ambulance kyukyu = new Ambulance();
        kyukyu.setTire(4);
        kyukyu.setGas();
        kyukyu.setNenpi();
        kyukyu.callSiren();
        System.out.println("===パトカー===");
        PatrolCar patrol = new PatrolCar();
        patrol.setTire(4);
        patrol.setGas();
        patrol.setNenpi();
        patrol.callSiren();
        patrol.drive();
        patrol.callSiren();
        patrol.drive();
        patrol.callSiren();
        patrol.drive();
        patrol.callSiren();
        patrol.drive();
    }
}