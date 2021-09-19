using System.Collections;
using UnityEngine;
using UnityEditor;
using System.IO;

public enum PrimitiveType
{
	CAMERA,
	CUBE,
	PLANE,
	SPHERE,
	CAPSULE
};

public class LevelLoader : EditorWindow
{
	[MenuItem("Tools/Load .level")]
	private static void Apply()
	{
		string path = EditorUtility.OpenFilePanel("Open .level file", "", "level");
		if (path.Length != 0)
		{
			string fileContent = File.ReadAllText(path);
			ParseData(fileContent);
		}
	}

    private static void ParseData(string asset)
    {
        string textContent = asset;
        string[] tempList = textContent.Split(new[] { "\r\n", "\r", "\n" }, System.StringSplitOptions.RemoveEmptyEntries);
        string[] rowContents = new string[0];
        int index = 0;

		string objectName = " ";
		PrimitiveType objectType = PrimitiveType.CAMERA;
		Vector3 position = Vector3.zero;
		Vector3 rotation = Vector3.zero;
		Vector3 scale = Vector3.one;
		int hasRigidBody = 0;

		for (int i = 0; i < tempList.Length; i++)
        {
			rowContents = tempList[i].Split(new[] { " " }, System.StringSplitOptions.RemoveEmptyEntries);
			if (index == 0)
			{
				objectName = rowContents[0];
				index++;
			}
			else if (index == 1)
			{
				if (int.TryParse(rowContents[1], out int x))
				{
					objectType = (PrimitiveType)x;
				}
				index++;
			}
			else if (index == 2)
			{
				float x = 0;
				float y = 0;
				float z = 0;
				if (float.TryParse(rowContents[1], out float a))
				{
					x = a;
				}
				if (float.TryParse(rowContents[2], out float b))
				{
					y = b;
				}
				if (float.TryParse(rowContents[3], out float c))
				{
					z = c;
				}
				position = new Vector3(x, y, z);
				index++;
			}
			else if (index == 3)
			{
				float x = 0;
				float y = 0;
				float z = 0;
				if (float.TryParse(rowContents[1], out float a))
				{
					x = a;
				}
				if (float.TryParse(rowContents[2], out float b))
				{
					y = b;
				}
				if (float.TryParse(rowContents[3], out float c))
				{
					z = c;
				}
				rotation = new Vector3(x * Mathf.Rad2Deg, y * Mathf.Rad2Deg, z * Mathf.Rad2Deg);
				index++;
			}
			else if (index == 4)
			{
				float x = 0;
				float y = 0;
				float z = 0;
				if (float.TryParse(rowContents[1], out float a))
				{
					x = a;
				}
				if (float.TryParse(rowContents[2], out float b))
				{
					y = b;
				}
				if (float.TryParse(rowContents[3], out float c))
				{
					z = c;
				}
				scale = new Vector3(x, y, z);
				index++;
			}
			else if (index == 5)
			{
				if (int.TryParse(rowContents[1], out int x))
				{
					hasRigidBody = x;
				}
				index = 0;

				switch (objectType)
				{
					case PrimitiveType.CUBE:
						GameObject newObject = GameObject.CreatePrimitive(UnityEngine.PrimitiveType.Cube);
						newObject.name = objectName;
						newObject.transform.position = position;
						newObject.transform.localScale = scale;
						newObject.transform.rotation = Quaternion.Euler(rotation);
						if (hasRigidBody == 1)
						{
							newObject.AddComponent<Rigidbody>();
						}
						else
						{
							DestroyImmediate(newObject.GetComponent<Collider>());
						}
						break;
					case PrimitiveType.PLANE:
						GameObject newPlane = GameObject.CreatePrimitive(UnityEngine.PrimitiveType.Plane);
						newPlane.name = objectName;
						newPlane.transform.position = position;
						newPlane.transform.localScale = scale * 0.1f;
						newPlane.transform.rotation = Quaternion.Euler(rotation);
						if (hasRigidBody == 0)
						{
							DestroyImmediate(newPlane.GetComponent<Collider>());
						}
						break;
					case PrimitiveType.SPHERE:
						GameObject newSphere = GameObject.CreatePrimitive(UnityEngine.PrimitiveType.Sphere);
						newSphere.name = objectName;
						newSphere.transform.position = position;
						newSphere.transform.localScale = scale;
						newSphere.transform.rotation = Quaternion.Euler(rotation);
						if (hasRigidBody == 1)
						{
							newSphere.AddComponent<Rigidbody>();
						}
						else
						{
							DestroyImmediate(newSphere.GetComponent<Collider>());
						}
						break;
					case PrimitiveType.CAPSULE:
						GameObject newCap = GameObject.CreatePrimitive(UnityEngine.PrimitiveType.Capsule);
						newCap.name = objectName;
						newCap.transform.position = position;
						newCap.transform.localScale = scale;
						newCap.transform.rotation = Quaternion.Euler(rotation);
						if (hasRigidBody == 1)
						{
							newCap.AddComponent<Rigidbody>();
						}
						else
						{
							DestroyImmediate(newCap.GetComponent<Collider>());
						}
						break;
					default:
						break;
				}
			}
        }
    }
}
