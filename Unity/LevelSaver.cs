using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;

public class LevelSaver : EditorWindow
{
	[MenuItem("Tools/Save as .level")]
	private static void Apply()
	{
		string path = EditorUtility.SaveFilePanel("Save .level file", "", "Scene.level", "level");
		if (path.Length != 0)
		{
			string output = encodeData();
			File.WriteAllText(path, output);
		}
	}

	private static string encodeData()
	{
		List<GameObject> primitives = new List<GameObject>();
		List<PrimitiveType> primitiveTypes = new List<PrimitiveType>();
		string[] meshNames = { "Cube", "Sphere", "Capsule", "Plane" };

		MeshFilter[] MeshFilters = FindObjectsOfType(typeof(MeshFilter)) as MeshFilter[];

		foreach (MeshFilter meshFilter in MeshFilters)
		{
			foreach (string name in meshNames)
			{
				if (name == meshFilter.sharedMesh.name)
				{
					primitives.Add(meshFilter.gameObject);
					switch(name)
                    {
						case "Cube":
							primitiveTypes.Add(PrimitiveType.CUBE);
							break;
						case "Sphere":
							primitiveTypes.Add(PrimitiveType.SPHERE);
							break;
						case "Capsule":
							primitiveTypes.Add(PrimitiveType.CAPSULE);
							break;
						case "Plane":
							primitiveTypes.Add(PrimitiveType.PLANE);
							break;
						default:
							break;
                    }
				}
			}
		}

		string output = "";
		for (int i = 0; i < primitives.Count; i++)
		{
			output += primitives[i].name + "\n";
			Vector3 pos = primitives[i].transform.position;
			Vector3 rot = primitives[i].transform.rotation.eulerAngles;
			Vector3 scale = primitives[i].transform.localScale;
			if (primitiveTypes[i] == PrimitiveType.PLANE)
				scale *= 10.0f;

			output += "Type: " + (int)primitiveTypes[i] + "\n";
			output += "Position: " + pos.x + " " + pos.y + " " + pos.z + "\n";
			output += "Rotation: " + rot.x * Mathf.Deg2Rad + " " + rot.y * Mathf.Deg2Rad + " " + rot.z * Mathf.Deg2Rad + "\n";
			output += "Scale: " + scale.x + " " + scale.y + " " + scale.z + "\n";

			if (primitives[i].GetComponent<Collider>() != null)
            {
				output += "HasRigidBody: 1\n";
			}
			else
            {
				output += "HasRigidBody: 0\n";
			}
		}
		return output;
	}
}
