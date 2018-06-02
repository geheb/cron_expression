public void MergeSourceFilesToSingleHeaderFile(string srcDir, string distDir)
{
	var code = new StringBuilder();

	var regexInclude = new System.Text.RegularExpressions.Regex(@"\s*#\s*include\s*""(.*)""",
		System.Text.RegularExpressions.RegexOptions.Compiled | System.Text.RegularExpressions.RegexOptions.IgnoreCase);

	var regexOnce = new System.Text.RegularExpressions.Regex(@"#pragma\s*once\s*",
		System.Text.RegularExpressions.RegexOptions.Compiled | System.Text.RegularExpressions.RegexOptions.IgnoreCase);

	foreach (var file in new[] {
		"date_time",
		"cron_field",
		"minute_field",
		"hour_field",
		"day_of_month_field",
		"month_field",
		"day_of_week_field",
		"cron_expression"})
	{
		foreach (var ext in new[] { ".h", ".cpp" })
		{
			string content = System.IO.File.ReadAllText(System.IO.Path.Combine(srcDir, file + ext));
			content = regexOnce.Replace(content, string.Empty);
			content = regexInclude.Replace(content, string.Empty);
			code.Append(content + "\n");
		}
	}

	var version = System.IO.File.ReadAllText("VERSION");
	var template = System.IO.File.ReadAllText(System.IO.Path.Combine("scripts", "file-template.txt"));
	var outputFile = System.IO.Path.Combine(distDir, "cron_expression.hpp");

	var now = DateTime.UtcNow;
	var output = template
		.Replace("{version}", version)
		.Replace("{timestamp}", now.ToString("o"))
		.Replace("{timestamp:year}", now.Year.ToString())
		.Replace("{content}", code.ToString());

	System.IO.File.WriteAllText(outputFile, output);
}
