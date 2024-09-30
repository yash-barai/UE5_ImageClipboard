The code captures image data from a Render Target, extracts the pixel information into a TArray<FColor>, and passes this data (along with image dimensions) to the CopyImageToClipboard function. 
This function handles formatting and copying the image data to the Windows clipboard. 

I followed a tutorial to copy text, which in itself was a struggle because it did not work with the latest release of UE5. After figuring out the issue and making changes it finally worked. 
Then I made a new project for copying image. I, unfortunately, failed at the task. At first the copy command was not executed itself. After modifying the code to what it is niw, it copies some data,
but not what the mock test provides. I have added what image is pasted labelled as ImageError.png

I would like to find out what I have done wrong and how to make the plugin work.Thank you for your time.
