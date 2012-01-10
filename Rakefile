
ROOT = File.dirname(__FILE__)

task :clean do

  # files
  files = [
    "**/Makefile",
    "bin/libmtv.*",
    "bin/libgsdl.*",
    "bin/librpg.*",
    "bin/pc",
    "bin/dm",
    "bin/table",
    "bin/pipeline",
    "bin/headless",
    "bin/mtv",
    "bin/udp",
    "bin/gsdl",
    "build/*",
    "**/*.o",    
    "**/moc_*",    
    "**/ui_*",
    "**/*~"
  ]

  files.each do |p|
    pattern = File.join(ROOT,p)
    Dir.glob(pattern).each do |file|
      system("rm -rf #{file}")
    end
  end

  #directories
  dirs = [
    "build"
  ]

  dirs.each do |d|
    name = File.join(ROOT,d)
    system("rm -rf #{name}") if File.directory?(name)
  end
  

end
