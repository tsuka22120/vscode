public class Main {
        public static void main(String[] args) {
                System.out.println("-----電気トラックを作ります-----");
                Car hino2t = new Truck(new MotorMovement());
                hino2t.back();
                hino2t.forward();
                hino2t.turn(false);
                System.out.println("-----ガソリンバスを作ります-----");
                Car isuzuBus = new Bus(new GasolineMovement());
                isuzuBus.forward();
                isuzuBus.turn(true);
                isuzuBus.back();
        }
}