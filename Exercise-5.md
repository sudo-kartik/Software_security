# Software Security in Practise

## Heartbleed security bug - 

It is a serious vulnerability in the OpenSSL cryptographic software library. Because of this stealing of information took place which is protected by the SSL/TLS encryption used to secure the internet.

SSL/TLS provides the communication security and privacy over the internet applications such as email, web, Virtual Private Network (VPN) etc.

This bug allows anyone on the internet to read the memory of the systems which is protected by the vulnerable version of OpenSSL software. Due to this the service providers secret key gets compromised which is used to encrypt the traffic, username, password and the rest content. 

this bug allowed the attacker to evedrop on ommunication, steal data and to impersonate services and users.

## Exploit -

First we will see that how TLS/SSL protocols operates -

Heartbeat is one of the important part of the TLS/SSL protocols by this computers communicate with each other and forward the message that they are still connected even there is no activity going on like uploading or downloading at that time. So here one computer will send an encrypted data to the other computer and the other computer will reply with the exact same encrypted data, proving that the connection is still in place. The heartbeat request always contains the the length of the information in it.

For example - if a user is reading his mail but does not done any anything for a while, so your web browser might send a heartbeat request to your mail server specifying that this is a 40 KB message you are about to get and send it back to me. When the mailing server will receive that message it will allocate a memmory bufer based on the reported length of the heartbeat request then it stores and read the data and send it back to the web browser.

The above is the standard Heartbeat request between the user web-browser and the server.

Now we will see the Exploit - 

The vulnerability arose because OpenSSL missing an important safegaurd in it. The computer which receives the heartbeat request never checks the length of the request, so it never make sure that the request is of same length as it mentioned. So if a request comes which shows that it of 40 KB but actually it is only of 20 KB then the receiving computer will set aside the 40 KB memory and send back the original 20 kB plus whatever information in the rest 20 KB of memory. So that extra 20 KB data is what attacker wants and extratcs from the server.

Even after all this when both the computer is done with the information exchange. The information is still present in the memory buffers untill something else comes and overwrite it.

After all this attacker can not know in advance what might he gets in that extra 20 KB, it could be gibberish or useless data. There can be the secret key which is used to encrypt the data and the attacker can use it to decrypt the secure communication but this is rarely the case, mostly it gets the username and  password of the users.


## Impact -

This bug alows the attacker to extract the memory content from the webserver through the vulnerability of the heartbeat, because of which the attacker may be able to access the sensitive content such as private keys used dfor SSL/TLS.

If the attacker gains the private key of the service provider, the attacker can silently monitor ans decrypt communications between the user and the web server. which means he can view the private data such as the username, password, credit card details, medical record and many other sensitive details of the user.

Sometimes an attacker gathers the sensitive information and stores it for later decryption. So by using this vulnerability the attacker can decrypt data if it was obtained when passed between a user and a vulnerable website. THis means that the data which was exchanged two year back can be at risk because of the exposure to the attacker.

OpenSSL version 1.0.1, 1.0.1-beta, 1.0.1f and d1.0.1-beta1 are affected by this bug. Apache, which uses OpenSSL for HTTPS, used by 66% of all websites according to netcraft.com. A study of the TLS heartbeat extension by Netcraft also identifies that 17.5% of SSL sites may be vulnerable to Heartbleed bug.[2]

## Why Undetected -

There are lot's of reasons why it does not detected for a long period of time -

-  The bug is very small so it is highly unlikely that a tester would able to detect the error since the tester would check the functionality and not go for checking the code line by line.
- the bug doesn't give any error when the code is run. Attackers leave no footprints and attacker can easily siphons the data from servers which make it impossible to detect when there is only a regular use.
- It needs a specialized testing which needs penetration testing and a very experienced security personels means it needs very intensive resources, which is hard for an open-source project.
- There is no software testing independently by the vendors moreover they put more focus on fixing the known bugs and building new features.
- As their is a blind trust on somthing which is open-source, there is a natural assumption that it is safe and all the bugs which is existed have been found and removed, so there is no need for wasting time on testing any further.

## Fix -

As the Vulnerability goes public, new and updated patches for OpenSSL comes out to fix the vulnerability.

The way to fix this vulnerability is to upgrade the OpenSSL version.

The patch in OpenSSL 1.0.1g is a bounds check, using the correct length in the SSL3 structure that describe the incoming heartbeat message.

Below is the revised code which is used to fix the bug - 

``` 
    hbtype = *p++;
   n2s(p, payload); 
   if (1 + 2 + payload + 16 > s->s3->rrec.length)
   return 0; /* silently discard per RFC 6520 sec. 4 */
   pl = p;
``` 
Part 1 of the code make sure that the heartbeat request is not of 0 KB, which can causes problems and the second part make sure that the request is as long as it mentioned.

If the server is left for the vulnerable for a long time period, so just updating the OpenSSL version is not sufficient, we should chamge the SSl certificate used by the servers, users should change the password as well.

Adding to this, Websites which already implemented perfect forward secrecy are protected against these type of attacks.



## References -

- [1] http://heartbleed.com/
- [2] https://www.owasp.org/index.php/Heartbleed_Bug#Defending_against_Vulnerability
- [3] https://www.csoonline.com/article/3223203/what-is-the-heartbleed-bug-how-does-it-work-and-how-was-it-fixed.html
- [4] https://www.quora.com/How-did-Heartbleed-go-overlooked-for-so-long
- [5] https://www.csoonline.com/article/3223203/what-is-the-heartbleed-bug-how-does-it-work-and-how-was-it-fixed.html

