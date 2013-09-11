(ns experiment.big-array
  (:require [domina :as dom]
            [domina.css :as css]))


(defn send-text-to-html [selector text]
  (dom/set-text! (css/sel "#"selector) (str text)))


(defn create-dummy-events
  "Create an array of integers according to a size provided in bytes."
  [size-in-byte]
  (let [nb-ints (int (/ size-in-byte 4))]
    (int-array nb-ints 0)))


(defn create-array-of-events
  "Create an array of events which is an array of array."
  [nb-of-events nb-of-bytes-per-events]
  (let [array-of-events (make-array nb-of-events)]
    (amap array-of-events i ret
          (aset array-of-events i (create-dummy-events nb-of-bytes-per-events)))))


(defn modify-an-event
  "Do some modification on the event which is an array of integers, here we increment each element of the event"  
  [event]
  (amap event i ret (aset event i (inc (aget event i)))))


(defn modify-all-events
  "Apply some modification on all events from an array of events"
  [events]
  (amap events i ret (aset events i (modify-an-event (aget events i)))))


(defn bench-array-creation 
  "Measure execution time for creating array of array similar to a list of events"
  [nb-events bytes-per-event]
  (let [elapsed-time
        (with-out-str
          (time (let [my-events (create-array-of-events nb-events bytes-per-event)]
                  (send-text-to-html "#nb-of-events-1" (count my-events))
                  (send-text-to-html "#nb-bytes-per-event-1" (* 4 (count (aget my-events 0))))
                  )))]
    (send-text-to-html "#bench-time-1" elapsed-time)
    elapsed-time))


(defn bench-array-addition
  "Measure execution time for modifying events from a list of events"
  [nb-events bytes-per-event]
  (let [my-events (create-array-of-events nb-events bytes-per-event)
        elapsed-time
        (with-out-str
          (time (modify-all-events my-events)))]
    (send-text-to-html "#nb-of-events-2" (count my-events))
    (send-text-to-html "#nb-bytes-per-event-2" (* 4 (count (aget my-events 0))))
    (send-text-to-html "#bench-time-2" elapsed-time)
    elapsed-time))


(defn ^:export main []
  (bench-array-creation 6000000 48)
  (bench-array-addition 6000000 48))
 
  
