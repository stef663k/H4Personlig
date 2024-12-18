from confluent_kafka import Consumer, KafkaException, KafkaError
from elasticsearch import Elasticsearch

es = Elasticsearch([{'host': '172.16.250.17', 'port': 9200, 'scheme': 'http'}])

consumer = Consumer({
    'bootstrap.servers': '172.16.250.12:9092',  
    'group.id': 'Stefan',  
    'auto.offset.reset': 'earliest'  
})

consumer.subscribe(['Gruppe1_Husstande'])

def consume_and_index():
    try:
        while True:
            msg = consumer.poll(timeout=1.0)  
            
            if msg is None:
                continue  
            if msg.error():
                if msg.error().code() == KafkaError._PARTITION_EOF:
                    print(f"End of partition reached {msg.topic()} [{msg.partition()}] @ {msg.offset()}")
                else:
                    raise KafkaException(msg.error())
            else:
                data = msg.value().decode('utf-8', errors='replace')  
                document = {
                    "Elmaaler_ID": data["Elmaaler_ID"],
                    "Elforbrug": data["Elforbrug"],
                    "Varmemaaler_ID": data["Varmemaaler_ID"],
                    "Varmeforbrug": data["Varmeforbrug"]
                }
                
                # Index data into Elasticsearch
                es.index(index="gruppe1_husstande", body=document)
                print(f"Indexed document: {document}")

    except KeyboardInterrupt:
        pass
    finally:
        consumer.close()

if __name__ == "__main__":
    consume_and_index()
