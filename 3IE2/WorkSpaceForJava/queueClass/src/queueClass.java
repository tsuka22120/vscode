class queueClass {
    static int defaultSize = 5;
    static int queue[] = new int[defaultSize];
    static int volume = 0;

    // キュー追加関数
    static void enqueue(int number) {
        if (queue.length > volume) {
            queue[volume] = number;
            volume++;
            System.out.printf("%d inserted\n", number);
        } else {
            System.out.printf("OverFlow\n");
        }
    }

    // キュー取得関数
    static int dequeue() {
        int returnValue = 0;
        if (volume > 0) {
            returnValue = queue[0];
            for (int i = 0; i < queue.length - 1; i++) {
                queue[i] = queue[i + 1];
            }
            queue[volume - 1] = 0;
            volume--;
        } else {
            System.out.printf("UnderFlow\n");
            returnValue = -1;
        }
        return returnValue;
    }

    // 状態表示関数
    static void printQueue() {
        System.out.printf("|");
        for (int i = 0; i < queue.length; i++) {
            System.out.printf("%d|", queue[i]);
        }
        System.out.println();
    }

    public static void main(String[] args) {
        enqueue(10);
        printQueue();
        enqueue(20);
        printQueue();
        enqueue(30);
        printQueue();
        enqueue(40);
        printQueue();
        enqueue(50);
        printQueue();
        enqueue(60);
        printQueue();
        System.out.printf("%d dequeued\n", dequeue());
        printQueue();
        System.out.printf("%d dequeued\n", dequeue());
        printQueue();
        System.out.printf("%d dequeued\n", dequeue());
        printQueue();
        System.out.printf("%d dequeued\n", dequeue());
        printQueue();
        System.out.printf("%d dequeued\n", dequeue());
        printQueue();
        System.out.printf("%d dequeued\n", dequeue());
        printQueue();
    }
}
