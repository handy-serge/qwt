(ns blacksmartie.client.stats.generate-csv
  "Outputs statistics data in CSV format.")

(defn generate-csv []
  (str "source;id;type\r\n"
       "plot;1;S\r\n"
       "gate;1:R\r\n"))
