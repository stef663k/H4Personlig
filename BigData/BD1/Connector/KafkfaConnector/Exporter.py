from prometheus_client import start_http_server, Gauge
from elasticsearch import Elasticsearch
import time

# Initialize Elasticsearch client
es = Elasticsearch([{'host': '172.16.250.17', 'port': 9200}])

# Create a Prometheus metric
el_energy_gauge = Gauge('el_energy_consumption', 'Electricity consumption per meter', ['Elmaaler_ID'])
heat_energy_gauge = Gauge('heat_energy_consumption', 'Heating consumption per meter', ['Varmemaaler_ID'])

def query_and_export_metrics():
    # Query Elasticsearch
    response = es.search(index="husstande_data", size=1000, body={"query": {"match_all": {}}})

    # Extract data from the response
    for hit in response['hits']['hits']:
        elmaaler_id = hit['_source']['Elmaaler_ID']
        elforbrug = hit['_source']['Elforbrug']
        varmemaaler_id = hit['_source']['Varmemaaler_ID']
        varmeforbrug = hit['_source']['Varmeforbrug']

        # Set the metrics for Prometheus
        el_energy_gauge.labels(Elmaaler_ID=elmaaler_id).set(elforbrug)
        heat_energy_gauge.labels(Varmemaaler_ID=varmemaaler_id).set(varmeforbrug)

def main():
    # Start the Prometheus metrics server on port 8000
    start_http_server(8000)
    while True:
        query_and_export_metrics()
        time.sleep(60)  # Update metrics every minute

if __name__ == '__main__':
    main()
