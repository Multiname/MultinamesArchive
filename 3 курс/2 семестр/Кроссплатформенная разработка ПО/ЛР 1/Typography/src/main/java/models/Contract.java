package models;

import jakarta.persistence.*;

@Entity
@Table(name = "Contracts")
public class Contract {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "Id")
    private long id;
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "ClientId")
    private Client client;
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "ProductId")
    private Product product;
    @Column(name = "Count")
    private int count;
    @Column(name = "Amount")
    private double amount;

    public Contract() {}
    public Contract(Client client, Product product, int count) {
        this.client = client;
        this.product = product;
        this.count = count;
    }

    public long GetId() { return id; }
    public Client GetClient() { return client; }
    public Product GetProduct() { return product; }
    public int GetCount() { return count; }
    public double GetAmount() { return amount; }

    public void SetClient(Client client) { this.client = client; }
    public void SetProduct(Product product) { this.product = product; }
    public void SetCount(int count) { this.count = count; }
}
