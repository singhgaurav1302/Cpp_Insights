# UML Class Relationship
1. Dependency
2. Association
   1. Aggregation 
   2. Composition
3. Inheritance
4. Realization

## Interpreting a relation

`Eg: Source depends on Target`

![PlantUML model](http://www.plantuml.com/plantuml/svg/SoWkIImgAStDuLBCp4lEAKr9LSWeAIcmqjSlBo_NAyX9p0D9wYNdv-h3EFh5PUdwmVdXsPwUkUcEmIKkfTvfhaucQHv6pgKvJa1sH92XiKbgZgTtONPfjf5Xf55AccboQ6A0fLzQiREvcNcHKwvtgd6f0PT3QbuAq400)

## Dependency
Dependency means that class A uses class B, but that **class A does not contain an instance of class B as part of its own state**. 
It also means that if class B’s interface changes it will likely impact class A and require it to change. 
I suggest that you constrain your use of dependency relationships to non-state related concerns. 

![Dependency](http://www.plantuml.com/plantuml/svg/SoWkIImgAStDuLBCp4lEAKr9LSWeAIcmqjSlBo_NAyX9p0D9wYNdv-h3EFh5PUdwmVdXsPwUkUcEmIKkfTuPha1sTaYIbxjZPPfpGNwKHsQHiq5bMN6fkQbJWNUgiQS1470vfEQb00q00000)

You would use dependency to indicate that, for example, class A receives an instance of class B 
as a parameter to at least one of its methods. 
You would also use dependency to indicate that class A creates an instance of class B local 
to one of its methods (on the stack). 

You would not, however, use dependency to indicate that class A declares an instance variable of class B, 
as that would indicate a state-related concern (state of an object i.e. member variables). 
Again, use association to do that.

```
public class A {
  public void method1 (B b) { // . . . }
  public void method2 () { B tempB = new B()
}
```

## Association

![Association](http://www.plantuml.com/plantuml/svg/SoWkIImgAStDuLBCp4lEAKr9LSWeAIcmqjSlBo_NAyX9p0D9wYNdv-h3EFh5PUdwmVdXsPwUkUcEmIKkfTuPha1sTaYIbxjJS9fpGNwKHvQFiq5bMN6fkQbJWNUgiQS1470vfEQb00q00000)

**Association defines dependency**, but a much stronger dependency than that described above with the plain dependency relationship. 

The arrowhead means that there is a one-way relationship. 

In this example it means that class A1 is associated with class B1. In other words, **class A1 uses and contains one instance of class B1**, but B1 does not know about or contain any instances of class A1.

```
public class A1 {
  private B1 b1;
  public B1 getB1() {
    return b1;
  }
}
```

Based on lifetime of the instances that make up the dependent object’s state they are further classified as:
1. Aggregation
2. Composition

### Aggregation

![Aggregation](http://www.plantuml.com/plantuml/svg/SoWkIImgAStDuLBCp4lEAKr9LSWeAIcmqjSlBo_NAyX9p0D9wYNdv-h3EFh5PUdwmVdXsPwUkUcEmIKkfNuMXJxEKNvEmMdE1VbH7Zv-1lbbvfOM1TwPXaRXpWPS3gbvAK2D0000)

**A1 aggregates B1.**

Aggregation describes an association **where an instance of A1 contains a reference to an instance of B1** as part of the A1’s state, but the use of the specific instance of B1 is or may be shared among other aggregators. 

A shared association means that the lifetime of the aggregated object i.e the instance of B1 in this case, is outside the scope of the referencing object. Therefore, **when a specific instance of A1 goes out of scope (e.g. garbage collected), the instance of B1 does not (of necessity) go out of scope**.

### Composition

![Composition](http://www.plantuml.com/plantuml/svg/SoWkIImgAStDuLBCp4lEAKr9LSWeAIcmqjSlBo_NAyX9p0D9wYNdv-h3EFh5PUdwmVdXsPwUkUcEmIKkfNuMXJuknfvEmMdE1VbH7Zv-1lbbvfOM1TwPXaRXpWPS3gbvAK2D0000)

Composition on the other hand defines a relationship where the **scope of the container object (an A1) and the contained object (a B1) is related**. 

When the **container object goes out of scope, then the contained object also goes out of scope**.

A1 goes out of scope then B1 also gets out of scope.

The composition adornment looks like the aggregation adornment, except the composition adornment is darkened

#### Aggregation

```
final class Car {
  private Engine engine;
  void setEngine(Engine engine) {
    this.engine = engine;
  }
  void move() {
    if (engine != null)
      engine.work();
  }
}
```

#### Composition

```
final class Car {
  private final Engine engine;
  Car(EngineSpecs specs) {
    engine = new Engine(specs);
  }
  void move() {
    engine.work();
  }
}
```

| Aggregation | Composition |
|--- | ---|
| Car also performs its functions through an Engine, but the Engine is not always an internal part of the Car. | Engine is completely encapsulated by the Car. There is no way for the outside world to get a reference to the Engine |
| **Engines may be swapped, or even completely removed** | **Engine lives and dies with the car** |
| The outside world can still have a reference to the Engine, and tinker with it regardless of whether it's in the Car | 
| Instance is created by some other class and referenced through getInstance() or returned from some function.| Instance is created in constructor. |


## Inheritance / Generalization
![Inheritance](http://www.plantuml.com/plantuml/svg/SoWkIImgAStDuLBCp4lEAKr9LSWeAIcmqjSlBo_NAyX9p0D9wYNdv-h3EFh5PUdwmVdXsPwUkUcEmIKkfNwMZaucPJxUJaPfXTubbawLyLu-VeQMJi6fcPw59H71YL4kdhccZWQv1WPS3gbvAK130000)

UML generalization is one of the better-understood relationships, and symbolizes what is known as inheritance in the world of object-oriented programming. It is sometimes also called specialization because the subclass is a specialization of the more generic super class.

`Base is inherited by Derived`

```
public class Derived : public Base { 
   // . . .
}
```

Base is the super class and Derived is the subclass in the relationship. Just remember that the generalization symbol forms a line from the subclass to its super class with the clear triangular arrowhead pointing at the super class


## Realization

![Realization](http://www.plantuml.com/plantuml/svg/SoWkIImgAStDuLBCp4lEAKr9LSWeAIcmqjSlBo_NAyX9p0D9wYNdv-h3EFh5PUdwmVdXsPwUkUcEmIKkfS4Ppew5YLcUYLdENaa-kPwHUQu-eGP6YGN-HQ4fgOvEwKccoRw-QOu-kQxfVebfxfRU1bmEgNafGCC0)

This relationship is somewhat related to generalization, but a bit different. 

In object-oriented programming parlance **realization represents the implementation of an interface by a class**

So it represents how some characteristics of a class are defined, but says nothing about the implementation details

This diagram fragment states that class A3 implements or realizes the interface defined by B3

```
public class A3 implements B3 {
  // . . .
}
```

## References:

https://vaughnvernon.co/?page_id=31

http://stackoverflow.com/questions/11881552/implementation-difference-between-aggregation-and-composition-in-java



