package models;

import jakarta.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "Clients")
public class Client {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "Id")
    private long id;
    @Column(name = "Name")
    private String name;
    @Column(name = "PhoneNumber")
    private long phoneNumber;
    @Column(name = "Sale")
    private double sale;
    @OneToMany(mappedBy = "client", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Contract> contracts;

    public Client() {}
    public Client(String name, long phoneNumber, double sale){
        this.name = name;
        this.phoneNumber = phoneNumber;
        this.sale = sale;
        contracts = new ArrayList<>();
    }

    public void AddContract(Contract contract) {
        contract.SetClient(this);
        contracts.add(contract);
    }
    public void RemoveContract(Contract contract) {
        contracts.remove(contract);
    }

    public long GetId() { return id; }
    public String GetName() { return name; }
    public long GetPhoneNumber() { return phoneNumber; }
    public double GetSale() { return sale; }
    public List<Contract> GetContracts() { return contracts; }

    public void SetName(String name) { this.name = name; }
    public void SetPhoneNumber(long phoneNumber) { this.phoneNumber = phoneNumber; }
    public void SetSale(double sale) { this.sale = sale; }
    public void SetContracts(List<Contract> contracts) { this.contracts = contracts; }
}
