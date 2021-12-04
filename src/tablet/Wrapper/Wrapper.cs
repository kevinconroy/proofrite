using System;

// The Ink namespace, which contains the Tablet PC Platform API
using Microsoft.Ink;
using System.Xml;
using System.Text;
using System.IO;
using System.Runtime.InteropServices;

namespace Wrapper
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	public class InkWrapper
	{
		public InkWrapper() 
		{
			// whatever man
			return;
		}

		// This function saves the form in XML format.
		// It uses the base64 encoded version of the ink, which is most suitable
		// for representation in XML. The names are stored as XML fields, rather
		// than custom properties, so that these properties can be most easily
		// accessible if the XML is saved in a database.
		public static string GetUTF8String(Microsoft.Ink.Ink ink)
		{
			// This object will encode our byte data to a UTF8 string
			UTF8Encoding utf8 = new UTF8Encoding();
            
			byte[] base64ISF_bytes;
			string base64ISF_string;

			// Get the base64 encoded ISF
			base64ISF_bytes = ink.Save(PersistenceFormat.Base64InkSerializedFormat);

			// Ink.Save returns a null terminated byte array. The encoding of the null
			// character generates a control sequence when it is UTF8 encoded. This
			// sequence is invalid in XML. Therefore, it is necessary to remove the 
			// null character before UTF8 encoding the array.
			// The following loop finds the index of the first non-null byte in the byte 
			// array returned by the Ink.Save method.
			int countOfBytesToConvertIntoString = base64ISF_bytes.Length - 1;
			for(; countOfBytesToConvertIntoString >= 0; --countOfBytesToConvertIntoString)
			{
				// Break the loop if the byte at the index is non-null.
				if(0 != base64ISF_bytes[countOfBytesToConvertIntoString])
					break;
			}

			// Convert the index into count by incrementing it.
			countOfBytesToConvertIntoString++;

			// Convert it to a String
			base64ISF_string = utf8.GetString(base64ISF_bytes, 0, countOfBytesToConvertIntoString);

			// return the xml-safe string
			return base64ISF_string;
		}
	}
}
