import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;

public class Main {
        public static void main(String args[]) {
                List<City> cityList = new ArrayList<City>();
                cityList.add(new City("Nagano", 361626, 834.81));
                cityList.add(new City("Matsumoto", 237304, 978.47));
                cityList.add(new City("Ueda", 150049, 552.04));
                cityList.add(new City("Okaya", 45418, 85.10));
                cityList.add(new City("Iida", 93529, 658.66));
                cityList.add(new City("Suwa", 47128, 109.17));
                cityList.add(new City("Suzaka", 48463, 149.67));
                for (int i = 0; i < cityList.size(); i++) {
                        System.out.println(i + ":" + cityList.get(i).getName() + " 人口:" +
                                        cityList.get(i).getPeople() + " 面積:" + cityList.get(i).getArea());
                }
                cityList.sort(new peopleComparator());
                for (int i = 0; i < cityList.size(); i++) {
                        System.out.println(i + ":" + cityList.get(i).getName() + " 人口:" +
                                        cityList.get(i).getPeople() + " 面積:" + cityList.get(i).getArea());
                }
                cityList.sort(new areaComparator());
                for (int i = 0; i < cityList.size(); i++) {
                        System.out.println(i + ":" + cityList.get(i).getName() + " 人口:" +
                                        cityList.get(i).getPeople() + " 面積:" + cityList.get(i).getArea());
                }
        }
}

class City {
        String name;
        int people;
        double area;

        City(String name, int people, double area) {
                setName(name);
                setPeople(people);
                setArea(area);
        }

        public String getName() {
                return name;
        }

        public void setName(String name) {
                this.name = name;
        }

        public int getPeople() {
                return people;
        }

        public void setPeople(int people) {
                this.people = people;
        }

        public double getArea() {
                return area;
        }

        public void setArea(double area) {
                this.area = area;
        }
}

class peopleComparator implements Comparator<City> {
        public int compare(City city1, City city2) {
                int people1 = city1.getPeople();
                int people2 = city2.getPeople();
                if (people1 > people2) {
                        return 1;
                } else if (people1 == people2) {
                        return 0;
                } else {
                        return -1;
                }
        }
}

class areaComparator implements Comparator<City> {
        public int compare(City city1, City city2) {
                double area1 = city1.getArea();
                double area2 = city2.getArea();
                if (area1 > area2) {
                        return 1;
                } else if (area1 == area2) {
                        return 0;
                } else {
                        return -1;
                }
        }
}