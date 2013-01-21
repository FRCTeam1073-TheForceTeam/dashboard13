(require "comm")

(defun rr-string-to-list (str)
   (do* ((stringstream (make-string-input-stream str))
         (result nil (cons next result))
         (next (read stringstream nil 'eos)
               (read stringstream nil 'eos)))
        ((equal next 'eos) (reverse result))))

(defun rr-replace-all (string part replacement &key (test #'char=))
"Returns a new string in which all the occurences of the part 
is replaced with replacement."
    (with-output-to-string (out)
      (loop with part-length = (length part)
            for old-pos = 0 then (+ pos part-length)
            for pos = (search part string
                              :start2 old-pos
                              :test test)
            do (write-string string out
                             :start old-pos
                             :end (or pos (length string)))
            when pos do (write-string replacement out)
            while pos))) 

(defun escapeXml(str)
  (setq str (rr-replace-all str "&" "&amp;"))
  (setq str (rr-replace-all str "<" "&lt;"))
  (setq str (rr-replace-all str ">" "&gt;"))
  (rr-replace-all str "\"" "&quot;"))

(defun sendMessage(requestType varName)
  (let ((newchar nil))
    (with-open-stream (talk (comm:open-tcp-stream "localhost" 6060 :errorp t))
       (format talk
               "<request><~A>~A</~A></request>"
               requestType (escapeXML varName) requestType)
       (force-output talk)
       (do ((response NIL (concatenate 'string response newchar)))
           ((search "</response>" response) response)
           (setq newchar (string (read-char talk)))))))

(defun sendValueMessage(requestType varName varValue)
  (let ((newchar nil))
    (with-open-stream (talk (comm:open-tcp-stream "localhost" 6060 :errorp t))
       (format talk
               "<request><~A><name>~A</name><value>~A</value></~A></request>"
               requestType varName varValue requestType)
       (force-output talk)
       (do ((response NIL (concatenate 'string response newchar)))
           ((search "</response>" response) response)
           (setq newchar (string (read-char talk)))))))

(defun sendTextMessage(str)
  (let ((newchar nil))
    (with-open-stream (talk (comm:open-tcp-stream "localhost" 6060 :errorp t))
       (format talk str)
       (force-output talk)
       (do ((response NIL (concatenate 'string response newchar)))
           ((search "</response>" response) response)
           (setq newchar (string (read-char talk)))))))

(defun parseResults(response)
  (let ((rlist nil))
    (setq response (subseq response 10))
    (setq response (subseq response 0 (- (length response) 11)))
    (setq response (substitute #\  #\< response))
    (setq response (substitute #\  #\/ response))
    (setq response (substitute #\  #\> response)) 
    (setq response (substitute #\_  #\, response))
    (setq rlist (rr-string-to-list response))
    (loop for i from 0 to (length rlist) by 3 
       collect (list (nth i rlist) (nth (+ i 1) rlist)))))

(defun parseQuickResult(response)
  (setq response (subseq response 10))
  (subseq response 0 (- (length response) 11)))

(defun getDimension()
  (let ((rlist (parseResults (sendMessage "get_dimension" ""))))
       (list (car (cdr (assoc 'width rlist))) (car (cdr (assoc 'height rlist))))))

(defun getVariable(varName)
  (car (cdr (assoc varName
    (parseResults (sendMessage "get_variable" (format nil "~A" varName))))))) 

(defun setVariable(varName varValue)
  (parseQuickResult (sendValueMessage "set_variable" varName varValue)))

(defun getVariables(varList)
  (let ((rlist (parseResults (sendTextMessage (format nil "<request><get_variables>~{~A~^,~}</get_variables></request>" varList)))))
  (loop for x in varList
     collect (car (cdr (assoc x rlist)))
  ))
)

(defun deleteVariable(varName)
  (parseQuickResult (sendMessage "delete_variable" varName)))

(defun execute(sourceXML)
  (parseQuickResult (sendMessage "execute" sourceXML)))

(defun loadProgram(filename)
  (parseQuickResult (sendMessage "load_program" filename)))

(defun getParameter(moduleName moduleCount paramName)
  (parseResults
    (sendTextMessage
      (format nil
        "<request><get_parameter><module>~A</module><module_count>~A</module_count><name>~A</name></get_parameter></request>"
        (escapeXML moduleName) moduleCount (escapeXML paramName)))))

(defun setParameter(moduleName moduleCount paramName paramValue)
  (parseQuickResult
    (sendTextMessage
      (format nil
        "<request><set_parameter><module>~A</module><module_count>~A</module_count><name>~A</name><value>~A</value></set_parameter></request>"
        (escapeXML moduleName) moduleCount (escapeXML paramName) (escapeXML paramValue)))))

(defun loadImage(markerName filename)
  (parseQuickResult
    (sendTextMessage
      (format nil
        "<request><load_image><name>~A</name><filename>~A</filename></load_image></request>"
        (escapeXML markerName) (escapeXML filename)))))

(defun saveImage(markerName filename)
  (parseQuickResult
    (sendTextMessage
      (format nil
        "<request><save_image><name>~A</name><filename>~A</filename></save_image></request>"
        (escapeXML markerName) (escapeXML filename)))))

; set the current camera OR turns the camera "off", "on" 
(defun setCamera(cameraName)
  (parseQuickResult (sendMessage "set_camera" cameraName)))

;mode can be toggle, on, off, once, or a number of frames to process
(defun run(mode)
  (parseQuickResult (sendMessage "run" mode)))

; waits for a variable to be equal to the specified value
(defun waitVariable(name value timeout)
  (parseQuickResult
    (sendTextMessage
      (format nil "<request><wait_variable><name>~A</name><value>~A</value><timeout>~A</timeout></wait_variable></request>" (escapeXML name) value timeout))))

; waits for a new image
(defun waitImage()
  (parseQuickResult
    (sendTextMessage (format nil "<request><wait_image></wait_image></request>"))))

; closes RoboRealm 
(defun closeRoboRealm()
  (parseQuickResult (sendTextMessage (format nil "<request><close></close></request>"))))

;(defun test()
  ;(getDimension)
  ;(princ (getVariable 'IMAGE_COUNT))
  ;(getVariable 'IMAGE_WIDTH)
  ;(getVariables (list 'IMAGE_WIDTH 'IMAGE_HEIGHT 'IMAGE_COUNT))

  ;(setVariable "test" "hello from lisp")
  ;(deleteVariable "test")

  ; send RGBFilter for red program
  ;(execute "<head><version>1.7</version></head><RGB_Filter><min_value>40</min_value><channel>1</channel></RGB_Filter>")

  ; load in a previously saved robo-file
  ;(loadProgram "c:\\temp\\red.robo")

  ; load in an image file
  ;(loadImage "source" "c:\\temp\\image1.jpg")

  ; save the processed image to an image file
  ;(saveImage "processed" "c:\\temp\\image2.jpg")

  ; switch camera, name must be part of camera string (see options dialog in RR)
  ;(setCamera "on")
  ;(setCamera "Logitech")
  ;(setCamera "CompUSA")

  ; roggle the run button ... this stops or starts processing
  ;(run "toggle")

  ; wait for a variable to equal a certain value ... can be used to pause a program until
  ; some condition is set
  ; (waitVariable "IMAGE_COUNT" 600 300000)

  ; wait for a new image to be captured
  ;(waitImage)

  ;(closeRoboRealm)

  ;example program 
  ;loads a Red filter program and captures the COG_X
  ;  (loadProgram "c:\\temp\\red-track.robo")
  ;  (princ leftMotor)
  ;  (princ rightMotor)
  ; now you could use the left and right motor variables to control Leaf's movement
  ; note that the red-track program is configured to maintain a value of 220 forward motion
  ; and adjust the left and right speed around that number to move in that direction. If
  ; you want to change the speed and turn values have a look at the VBScript module in 
  ; RR that computes that ratio ...
;)

(defun test()
  '(princ (getVariables (list 'LEFT_MOTOR 'RIGHT_MOTOR)))
  (princ (getVariable 'Laser_Points))
nil)
