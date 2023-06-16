package models;

import jakarta.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "Products")
public class Product {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "Id")
    private long id;
    @Column(name = "Name")
    private String name;
    @Column(name = "Price")
    private double price;
    @OneToMany(mappedBy = "product", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Contract> contracts;

    public Product() {}
    public Product(String name, double price) {
        this.name = name;
        this.price = price;
        contracts = new ArrayList<>();
    }

    public void AddContract(Contract contract) {
        contract.SetProduct(this);
        contracts.add(contract);
    }
    public void RemoveContract(Contract contract) {
        contracts.remove(contract);
    }

    public long GetId() { return id; }
    public String GetName() { return name; }
    public double GetPrice() { return price; }
    public List<Contract> GetContracts() { return contracts; }

    public void SetName(String name) { this.name = name; }
    public void SetPrice(double price) { this.price = price; }
    public void SetContracts(List<Contract> contracts) { this.contracts = contracts; }
}
