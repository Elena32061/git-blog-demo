// See README.md for license details.

ThisBuild / scalaVersion     := "2.12.13"
ThisBuild / version          := "1.0.0"
ThisBuild / organization     := "mycompany"
ThisBuild / transitiveClassifiers := Seq(Artifact.SourceClassifier)

resolvers ++= Seq(
  Resolver.sonatypeRepo("snapshots"),
  Resolver.sonatypeRepo("releases")
)

lazy val root = (project in file("."))
  .settings(
    name := "LUSOC",
    libraryDependencies ++= Seq(
      "edu.berkeley.cs" %% "chisel3" % "3.5-SNAPSHOT",
      "org.easysoc" %% "layered-firrtl" % "1.1-SNAPSHOT",
      "edu.berkeley.cs" %% "chiseltest" % "0.5-SNAPSHOT" % "test"
    ),
    scalacOptions ++= Seq(
      "-language:reflectiveCalls",
      "-deprecation",
      "-feature",
      "-Xcheckinit"
    ),
    addCompilerPlugin("org.scalamacros" % "paradise" % "2.1.1" cross CrossVersion.full),
    addCompilerPlugin("edu.berkeley.cs" % "chisel3-plugin" % "3.5-SNAPSHOT" cross CrossVersion.full)
  )


